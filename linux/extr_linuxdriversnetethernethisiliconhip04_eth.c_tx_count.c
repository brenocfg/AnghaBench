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

/* Variables and functions */
 int TX_DESC_NUM ; 

__attribute__((used)) static inline unsigned int tx_count(unsigned int head, unsigned int tail)
{
	return (head - tail) % (TX_DESC_NUM - 1);
}