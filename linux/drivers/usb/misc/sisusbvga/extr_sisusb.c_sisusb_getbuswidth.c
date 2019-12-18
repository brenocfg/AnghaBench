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
typedef  int u8 ;
typedef  int u32 ;
struct sisusb_usb_data {int dummy; } ;

/* Variables and functions */
 int GETIREG (int /*<<< orphan*/ ,int,int*) ; 
 int READL (int,int*) ; 
 int SETIREG (int /*<<< orphan*/ ,int,int) ; 
 int SETIREGAND (int /*<<< orphan*/ ,int,int) ; 
 int SETIREGANDOR (int /*<<< orphan*/ ,int,int,int) ; 
 int SETIREGOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SISSR ; 
 int SISUSB_PCI_MEMBASE ; 
 int WRITEL (int,int) ; 
 int sisusb_triggersr16 (struct sisusb_usb_data*,int) ; 

__attribute__((used)) static int sisusb_getbuswidth(struct sisusb_usb_data *sisusb,
		int *bw, int *chab)
{
	int ret;
	u8  ramtype, done = 0;
	u32 t0, t1, t2, t3;
	u32 ramptr = SISUSB_PCI_MEMBASE;

	ret = GETIREG(SISSR, 0x3a, &ramtype);
	ramtype &= 3;

	ret |= SETIREG(SISSR, 0x13, 0x00);

	if (ramtype <= 1) {
		ret |= SETIREG(SISSR, 0x14, 0x12);
		ret |= SETIREGAND(SISSR, 0x15, 0xef);
	} else {
		ret |= SETIREG(SISSR, 0x14, 0x02);
	}

	ret |= sisusb_triggersr16(sisusb, ramtype);
	ret |= WRITEL(ramptr +  0, 0x01234567);
	ret |= WRITEL(ramptr +  4, 0x456789ab);
	ret |= WRITEL(ramptr +  8, 0x89abcdef);
	ret |= WRITEL(ramptr + 12, 0xcdef0123);
	ret |= WRITEL(ramptr + 16, 0x55555555);
	ret |= WRITEL(ramptr + 20, 0x55555555);
	ret |= WRITEL(ramptr + 24, 0xffffffff);
	ret |= WRITEL(ramptr + 28, 0xffffffff);
	ret |= READL(ramptr +  0, &t0);
	ret |= READL(ramptr +  4, &t1);
	ret |= READL(ramptr +  8, &t2);
	ret |= READL(ramptr + 12, &t3);

	if (ramtype <= 1) {

		*chab = 0; *bw = 64;

		if ((t3 != 0xcdef0123) || (t2 != 0x89abcdef)) {
			if ((t1 == 0x456789ab) && (t0 == 0x01234567)) {
				*chab = 0; *bw = 64;
				ret |= SETIREGAND(SISSR, 0x14, 0xfd);
			}
		}
		if ((t1 != 0x456789ab) || (t0 != 0x01234567)) {
			*chab = 1; *bw = 64;
			ret |= SETIREGANDOR(SISSR, 0x14, 0xfc, 0x01);

			ret |= sisusb_triggersr16(sisusb, ramtype);
			ret |= WRITEL(ramptr +  0, 0x89abcdef);
			ret |= WRITEL(ramptr +  4, 0xcdef0123);
			ret |= WRITEL(ramptr +  8, 0x55555555);
			ret |= WRITEL(ramptr + 12, 0x55555555);
			ret |= WRITEL(ramptr + 16, 0xaaaaaaaa);
			ret |= WRITEL(ramptr + 20, 0xaaaaaaaa);
			ret |= READL(ramptr +  4, &t1);

			if (t1 != 0xcdef0123) {
				*bw = 32;
				ret |= SETIREGOR(SISSR, 0x15, 0x10);
			}
		}

	} else {

		*chab = 0; *bw = 64;	/* default: cha, bw = 64 */

		done = 0;

		if (t1 == 0x456789ab) {
			if (t0 == 0x01234567) {
				*chab = 0; *bw = 64;
				done = 1;
			}
		} else {
			if (t0 == 0x01234567) {
				*chab = 0; *bw = 32;
				ret |= SETIREG(SISSR, 0x14, 0x00);
				done = 1;
			}
		}

		if (!done) {
			ret |= SETIREG(SISSR, 0x14, 0x03);
			ret |= sisusb_triggersr16(sisusb, ramtype);

			ret |= WRITEL(ramptr +  0, 0x01234567);
			ret |= WRITEL(ramptr +  4, 0x456789ab);
			ret |= WRITEL(ramptr +  8, 0x89abcdef);
			ret |= WRITEL(ramptr + 12, 0xcdef0123);
			ret |= WRITEL(ramptr + 16, 0x55555555);
			ret |= WRITEL(ramptr + 20, 0x55555555);
			ret |= WRITEL(ramptr + 24, 0xffffffff);
			ret |= WRITEL(ramptr + 28, 0xffffffff);
			ret |= READL(ramptr +  0, &t0);
			ret |= READL(ramptr +  4, &t1);

			if (t1 == 0x456789ab) {
				if (t0 == 0x01234567) {
					*chab = 1; *bw = 64;
					return ret;
				} /* else error */
			} else {
				if (t0 == 0x01234567) {
					*chab = 1; *bw = 32;
					ret |= SETIREG(SISSR, 0x14, 0x01);
				} /* else error */
			}
		}
	}
	return ret;
}