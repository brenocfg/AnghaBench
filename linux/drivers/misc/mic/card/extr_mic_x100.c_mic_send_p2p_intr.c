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
struct mic_mw {int dummy; } ;

/* Variables and functions */
 int MIC_X100_NUM_SBOX_IRQ ; 
 int /*<<< orphan*/  mic_x100_send_rdmasr_intr (struct mic_mw*,int) ; 
 int /*<<< orphan*/  mic_x100_send_sbox_intr (struct mic_mw*,int) ; 

void mic_send_p2p_intr(int db, struct mic_mw *mw)
{
	int rdmasr_index;

	if (db < MIC_X100_NUM_SBOX_IRQ) {
		mic_x100_send_sbox_intr(mw, db);
	} else {
		rdmasr_index = db - MIC_X100_NUM_SBOX_IRQ;
		mic_x100_send_rdmasr_intr(mw, rdmasr_index);
	}
}