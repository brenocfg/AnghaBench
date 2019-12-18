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
typedef  int u16 ;
struct vnt_private {int basic_rates; int top_ofdm_basic_rate; int top_cck_basic_rate; } ;

/* Variables and functions */
 int RATE_11M ; 
 int RATE_1M ; 
 int RATE_24M ; 
 int RATE_54M ; 
 int RATE_6M ; 

void vnt_update_top_rates(struct vnt_private *priv)
{
	u8 top_ofdm = RATE_24M, top_cck = RATE_1M;
	u8 i;

	/*Determines the highest basic rate.*/
	for (i = RATE_54M; i >= RATE_6M; i--) {
		if (priv->basic_rates & (u16)(1 << i)) {
			top_ofdm = i;
			break;
		}
	}

	priv->top_ofdm_basic_rate = top_ofdm;

	for (i = RATE_11M;; i--) {
		if (priv->basic_rates & (u16)(1 << i)) {
			top_cck = i;
			break;
		}
		if (i == RATE_1M)
			break;
	}

	priv->top_cck_basic_rate = top_cck;
}