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
struct adapter {int flags; int /*<<< orphan*/  use_bd; } ;

/* Variables and functions */
 int FW_OK ; 

__attribute__((used)) static unsigned int t4_use_ldst(struct adapter *adap)
{
	return (adap->flags & FW_OK) && !adap->use_bd;
}