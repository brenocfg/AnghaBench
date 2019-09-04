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
 scalar_t__ PCNET32_WIO_RESET ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 

__attribute__((used)) static void pcnet32_wio_reset(unsigned long addr)
{
	inw(addr + PCNET32_WIO_RESET);
}