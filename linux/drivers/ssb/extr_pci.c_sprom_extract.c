#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct ssb_sprom {int revision; int boardflags_lo; int boardflags_hi; struct ssb_sprom* et1mac; struct ssb_sprom* et0mac; } ;
struct ssb_bus {int chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ssb_sprom*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  sprom_extract_r123 (struct ssb_sprom*,int const*) ; 
 int /*<<< orphan*/  sprom_extract_r45 (struct ssb_sprom*,int const*) ; 
 int /*<<< orphan*/  sprom_extract_r8 (struct ssb_sprom*,int const*) ; 

__attribute__((used)) static int sprom_extract(struct ssb_bus *bus, struct ssb_sprom *out,
			 const u16 *in, u16 size)
{
	memset(out, 0, sizeof(*out));

	out->revision = in[size - 1] & 0x00FF;
	pr_debug("SPROM revision %d detected\n", out->revision);
	memset(out->et0mac, 0xFF, 6);		/* preset et0 and et1 mac */
	memset(out->et1mac, 0xFF, 6);

	if ((bus->chip_id & 0xFF00) == 0x4400) {
		/* Workaround: The BCM44XX chip has a stupid revision
		 * number stored in the SPROM.
		 * Always extract r1. */
		out->revision = 1;
		pr_debug("SPROM treated as revision %d\n", out->revision);
	}

	switch (out->revision) {
	case 1:
	case 2:
	case 3:
		sprom_extract_r123(out, in);
		break;
	case 4:
	case 5:
		sprom_extract_r45(out, in);
		break;
	case 8:
		sprom_extract_r8(out, in);
		break;
	default:
		pr_warn("Unsupported SPROM revision %d detected. Will extract v1\n",
			out->revision);
		out->revision = 1;
		sprom_extract_r123(out, in);
	}

	if (out->boardflags_lo == 0xFFFF)
		out->boardflags_lo = 0;  /* per specs */
	if (out->boardflags_hi == 0xFFFF)
		out->boardflags_hi = 0;  /* per specs */

	return 0;
}