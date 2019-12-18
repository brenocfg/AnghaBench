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
typedef  int /*<<< orphan*/  u32 ;
struct ksz_device {int /*<<< orphan*/ * regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_CTRL_ADDR (int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz9477_port_cfg32(struct ksz_device *dev, int port, int offset,
			       u32 bits, bool set)
{
	regmap_update_bits(dev->regmap[2], PORT_CTRL_ADDR(port, offset),
			   bits, set ? bits : 0);
}