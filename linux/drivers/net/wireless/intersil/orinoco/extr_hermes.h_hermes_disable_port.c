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
struct hermes {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* cmd_wait ) (struct hermes*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int HERMES_CMD_DISABLE ; 
 int stub1 (struct hermes*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int hermes_disable_port(struct hermes *hw, int port)
{
	return hw->ops->cmd_wait(hw, HERMES_CMD_DISABLE | (port << 8),
				 0, NULL);
}