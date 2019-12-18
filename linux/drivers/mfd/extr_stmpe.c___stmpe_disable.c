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
struct stmpe {TYPE_1__* variant; } ;
struct TYPE_2__ {int (* enable ) (struct stmpe*,unsigned int,int) ;} ;

/* Variables and functions */
 int stub1 (struct stmpe*,unsigned int,int) ; 

__attribute__((used)) static int __stmpe_disable(struct stmpe *stmpe, unsigned int blocks)
{
	return stmpe->variant->enable(stmpe, blocks, false);
}