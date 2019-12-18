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
typedef  int /*<<< orphan*/  u8 ;
struct fritzcard {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVM_ISAC_FIFO ; 
 scalar_t__ CHIP_INDEX ; 
 scalar_t__ CHIP_WINDOW ; 
 int /*<<< orphan*/  insb (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ReadFiFoISAC_V1(void *p, u8 off, u8 *data, int size)
{
	struct fritzcard *fc = p;

	outb(AVM_ISAC_FIFO, fc->addr + CHIP_INDEX);
	insb(fc->addr + CHIP_WINDOW, data, size);
}