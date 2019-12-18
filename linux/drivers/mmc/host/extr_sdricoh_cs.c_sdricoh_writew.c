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
struct sdricoh_host {int /*<<< orphan*/  dev; scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned short) ; 
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline void sdricoh_writew(struct sdricoh_host *host, unsigned int reg,
					 unsigned short value)
{
	writew(value, host->iobase + reg);
	dev_vdbg(host->dev, "ww %x 0x%x\n", reg, value);
}