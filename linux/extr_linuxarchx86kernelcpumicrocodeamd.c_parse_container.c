#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ processor_rev_id; } ;
struct microcode_amd {TYPE_1__ hdr; } ;
struct equiv_cpu_entry {int dummy; } ;
struct cont_desc {int size; int /*<<< orphan*/ * data; struct microcode_amd* mc; scalar_t__ psize; int /*<<< orphan*/  cpuid_1_eax; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int CONTAINER_HDR_SZ ; 
 scalar_t__ PATCH_MAX_SIZE ; 
 int SECTION_HDR_SIZE ; 
 scalar_t__ UCODE_EQUIV_CPU_TABLE_TYPE ; 
 scalar_t__ UCODE_MAGIC ; 
 scalar_t__ UCODE_UCODE_TYPE ; 
 scalar_t__ find_equiv_id (struct equiv_cpu_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t parse_container(u8 *ucode, ssize_t size, struct cont_desc *desc)
{
	struct equiv_cpu_entry *eq;
	ssize_t orig_size = size;
	u32 *hdr = (u32 *)ucode;
	u16 eq_id;
	u8 *buf;

	/* Am I looking at an equivalence table header? */
	if (hdr[0] != UCODE_MAGIC ||
	    hdr[1] != UCODE_EQUIV_CPU_TABLE_TYPE ||
	    hdr[2] == 0)
		return CONTAINER_HDR_SZ;

	buf = ucode;

	eq = (struct equiv_cpu_entry *)(buf + CONTAINER_HDR_SZ);

	/* Find the equivalence ID of our CPU in this table: */
	eq_id = find_equiv_id(eq, desc->cpuid_1_eax);

	buf  += hdr[2] + CONTAINER_HDR_SZ;
	size -= hdr[2] + CONTAINER_HDR_SZ;

	/*
	 * Scan through the rest of the container to find where it ends. We do
	 * some basic sanity-checking too.
	 */
	while (size > 0) {
		struct microcode_amd *mc;
		u32 patch_size;

		hdr = (u32 *)buf;

		if (hdr[0] != UCODE_UCODE_TYPE)
			break;

		/* Sanity-check patch size. */
		patch_size = hdr[1];
		if (patch_size > PATCH_MAX_SIZE)
			break;

		/* Skip patch section header: */
		buf  += SECTION_HDR_SIZE;
		size -= SECTION_HDR_SIZE;

		mc = (struct microcode_amd *)buf;
		if (eq_id == mc->hdr.processor_rev_id) {
			desc->psize = patch_size;
			desc->mc = mc;
		}

		buf  += patch_size;
		size -= patch_size;
	}

	/*
	 * If we have found a patch (desc->mc), it means we're looking at the
	 * container which has a patch for this CPU so return 0 to mean, @ucode
	 * already points to the proper container. Otherwise, we return the size
	 * we scanned so that we can advance to the next container in the
	 * buffer.
	 */
	if (desc->mc) {
		desc->data = ucode;
		desc->size = orig_size - size;

		return 0;
	}

	return orig_size - size;
}