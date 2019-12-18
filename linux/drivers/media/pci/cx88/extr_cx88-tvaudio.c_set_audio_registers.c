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
struct rlist {int reg; int /*<<< orphan*/  val; } ;
struct cx88_core {int dummy; } ;

/* Variables and functions */
#define  AUD_PDF_DDS_CNST_BYTE0 133 
#define  AUD_PDF_DDS_CNST_BYTE1 132 
#define  AUD_PDF_DDS_CNST_BYTE2 131 
#define  AUD_PHACC_FREQ_8LSB 130 
#define  AUD_PHACC_FREQ_8MSB 129 
#define  AUD_QAM_MODE 128 
 int /*<<< orphan*/  cx_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_audio_registers(struct cx88_core *core, const struct rlist *l)
{
	int i;

	for (i = 0; l[i].reg; i++) {
		switch (l[i].reg) {
		case AUD_PDF_DDS_CNST_BYTE2:
		case AUD_PDF_DDS_CNST_BYTE1:
		case AUD_PDF_DDS_CNST_BYTE0:
		case AUD_QAM_MODE:
		case AUD_PHACC_FREQ_8MSB:
		case AUD_PHACC_FREQ_8LSB:
			cx_writeb(l[i].reg, l[i].val);
			break;
		default:
			cx_write(l[i].reg, l[i].val);
			break;
		}
	}
}