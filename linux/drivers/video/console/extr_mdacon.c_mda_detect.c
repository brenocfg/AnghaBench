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

/* Variables and functions */
 int MDA_STATUS_VSYNC ; 
 int /*<<< orphan*/  TYPE_HERC ; 
 int /*<<< orphan*/  TYPE_HERCCOLOR ; 
 int /*<<< orphan*/  TYPE_HERCPLUS ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mda_status_port ; 
 int /*<<< orphan*/  mda_type ; 
 char* mda_type_name ; 
 int* mda_vram_base ; 
 int mda_vram_len ; 
 int scr_readw (int*) ; 
 int /*<<< orphan*/  scr_writew (int,int*) ; 
 int /*<<< orphan*/  test_mda_b (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mda_detect(void)
{
	int count=0;
	u16 *p, p_save;
	u16 *q, q_save;

	/* do a memory check */

	p = mda_vram_base;
	q = mda_vram_base + 0x01000 / 2;

	p_save = scr_readw(p);
	q_save = scr_readw(q);

	scr_writew(0xAA55, p);
	if (scr_readw(p) == 0xAA55)
		count++;

	scr_writew(0x55AA, p);
	if (scr_readw(p) == 0x55AA)
		count++;

	scr_writew(p_save, p);

	if (count != 2) {
		return 0;
	}

	/* check if we have 4K or 8K */

	scr_writew(0xA55A, q);
	scr_writew(0x0000, p);
	if (scr_readw(q) == 0xA55A)
		count++;
	
	scr_writew(0x5AA5, q);
	scr_writew(0x0000, p);
	if (scr_readw(q) == 0x5AA5)
		count++;

	scr_writew(p_save, p);
	scr_writew(q_save, q);
	
	if (count == 4) {
		mda_vram_len = 0x02000;
	}
	
	/* Ok, there is definitely a card registering at the correct
	 * memory location, so now we do an I/O port test.
	 */

#ifdef TEST_MDA_B
	/* Edward: These two mess `tests' mess up my cursor on bootup */

	/* cursor low register */
	if (!test_mda_b(0x66, 0x0f))
		return 0;

	/* cursor low register */
	if (!test_mda_b(0x99, 0x0f))
		return 0;
#endif

	/* See if the card is a Hercules, by checking whether the vsync
	 * bit of the status register is changing.  This test lasts for
	 * approximately 1/10th of a second.
	 */
	
	p_save = q_save = inb_p(mda_status_port) & MDA_STATUS_VSYNC;

	for (count = 0; count < 50000 && p_save == q_save; count++) {
		q_save = inb(mda_status_port) & MDA_STATUS_VSYNC;
		udelay(2);
	}

	if (p_save != q_save) {
		switch (inb_p(mda_status_port) & 0x70) {
		case 0x10:
			mda_type = TYPE_HERCPLUS;
			mda_type_name = "HerculesPlus";
			break;
		case 0x50:
			mda_type = TYPE_HERCCOLOR;
			mda_type_name = "HerculesColor";
			break;
		default:
			mda_type = TYPE_HERC;
			mda_type_name = "Hercules";
			break;
		}
	}

	return 1;
}