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
typedef  int u16 ;
struct airo_info {TYPE_1__* dev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_MPI ; 
 int /*<<< orphan*/  do8bitIO ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void OUT4500( struct airo_info *ai, u16 reg, u16 val ) {
	if (test_bit(FLAG_MPI,&ai->flags))
		reg <<= 1;
	if ( !do8bitIO )
		outw( val, ai->dev->base_addr + reg );
	else {
		outb( val & 0xff, ai->dev->base_addr + reg );
		outb( val >> 8, ai->dev->base_addr + reg + 1 );
	}
}