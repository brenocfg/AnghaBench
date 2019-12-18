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
struct TYPE_2__ {scalar_t__ rx_stream; } ;
struct ar9170 {TYPE_1__ fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __carl9170_rx (struct ar9170*,void*,unsigned int) ; 
 int /*<<< orphan*/  carl9170_rx_stream (struct ar9170*,void*,unsigned int) ; 

void carl9170_rx(struct ar9170 *ar, void *buf, unsigned int len)
{
	if (ar->fw.rx_stream)
		carl9170_rx_stream(ar, buf, len);
	else
		__carl9170_rx(ar, buf, len);
}