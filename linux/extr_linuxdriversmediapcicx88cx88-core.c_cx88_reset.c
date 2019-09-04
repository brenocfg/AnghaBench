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
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_AGC_BACK_VBI ; 
 int /*<<< orphan*/  MO_AGC_SYNC_TIP1 ; 
 int /*<<< orphan*/  MO_COLOR_CTRL ; 
 int /*<<< orphan*/  MO_INPUT_FORMAT ; 
 int /*<<< orphan*/  MO_INT1_STAT ; 
 int /*<<< orphan*/  MO_PCI_INTSTAT ; 
 int /*<<< orphan*/  MO_PDMA_DTHRSH ; 
 int /*<<< orphan*/  MO_PDMA_STHRSH ; 
 int /*<<< orphan*/  MO_SRST_IO ; 
 int /*<<< orphan*/  MO_VID_INTSTAT ; 
 size_t SRAM_CH21 ; 
 size_t SRAM_CH22 ; 
 size_t SRAM_CH23 ; 
 size_t SRAM_CH24 ; 
 size_t SRAM_CH25 ; 
 size_t SRAM_CH26 ; 
 size_t SRAM_CH27 ; 
 size_t SRAM_CH28 ; 
 int /*<<< orphan*/  cx88_shutdown (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_sram_channel_setup (struct cx88_core*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cx88_sram_channels ; 
 int /*<<< orphan*/  cx_andor (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int cx88_reset(struct cx88_core *core)
{
	dprintk(1, "");
	cx88_shutdown(core);

	/* clear irq status */
	cx_write(MO_VID_INTSTAT, 0xFFFFFFFF); // Clear PIV int
	cx_write(MO_PCI_INTSTAT, 0xFFFFFFFF); // Clear PCI int
	cx_write(MO_INT1_STAT,   0xFFFFFFFF); // Clear RISC int

	/* wait a bit */
	msleep(100);

	/* init sram */
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH21],
				720 * 4, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH22], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH23], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH24], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH25], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH26], 128, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH28],
				188 * 4, 0);
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH27], 128, 0);

	/* misc init ... */
	cx_write(MO_INPUT_FORMAT, ((1 << 13) |   // agc enable
				   (1 << 12) |   // agc gain
				   (1 << 11) |   // adaptibe agc
				   (0 << 10) |   // chroma agc
				   (0 <<  9) |   // ckillen
				   (7)));

	/* setup image format */
	cx_andor(MO_COLOR_CTRL, 0x4000, 0x4000);

	/* setup FIFO Thresholds */
	cx_write(MO_PDMA_STHRSH,   0x0807);
	cx_write(MO_PDMA_DTHRSH,   0x0807);

	/* fixes flashing of image */
	cx_write(MO_AGC_SYNC_TIP1, 0x0380000F);
	cx_write(MO_AGC_BACK_VBI,  0x00E00555);

	cx_write(MO_VID_INTSTAT,   0xFFFFFFFF); // Clear PIV int
	cx_write(MO_PCI_INTSTAT,   0xFFFFFFFF); // Clear PCI int
	cx_write(MO_INT1_STAT,     0xFFFFFFFF); // Clear RISC int

	/* Reset on-board parts */
	cx_write(MO_SRST_IO, 0);
	usleep_range(10000, 20000);
	cx_write(MO_SRST_IO, 1);

	return 0;
}