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
struct nx842_crypto_header {TYPE_1__* group; int /*<<< orphan*/  groups; } ;
struct TYPE_2__ {int /*<<< orphan*/  padding; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EINVAL ; 
 int NX842_CRYPTO_HEADER_SIZE (int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nx842_crypto_header*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nx842_crypto_add_header(struct nx842_crypto_header *hdr, u8 *buf)
{
	int s = NX842_CRYPTO_HEADER_SIZE(hdr->groups);

	/* compress should have added space for header */
	if (s > be16_to_cpu(hdr->group[0].padding)) {
		pr_err("Internal error: no space for header\n");
		return -EINVAL;
	}

	memcpy(buf, hdr, s);

	print_hex_dump_debug("header ", DUMP_PREFIX_OFFSET, 16, 1, buf, s, 0);

	return 0;
}