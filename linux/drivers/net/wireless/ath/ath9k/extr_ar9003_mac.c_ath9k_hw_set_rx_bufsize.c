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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DATABUF_SIZE ; 
 int AR_DATABUF_SIZE_MASK ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 

void ath9k_hw_set_rx_bufsize(struct ath_hw *ah, u16 buf_size)
{
	REG_WRITE(ah, AR_DATABUF_SIZE, buf_size & AR_DATABUF_SIZE_MASK);
}