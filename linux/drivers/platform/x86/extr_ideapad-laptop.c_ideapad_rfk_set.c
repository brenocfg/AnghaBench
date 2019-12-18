#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ideapad_rfk_priv {size_t dev; TYPE_2__* priv; } ;
struct TYPE_6__ {int opcode; } ;
struct TYPE_5__ {TYPE_1__* adev; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 TYPE_3__* ideapad_rfk_data ; 
 int write_ec_cmd (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ideapad_rfk_set(void *data, bool blocked)
{
	struct ideapad_rfk_priv *priv = data;
	int opcode = ideapad_rfk_data[priv->dev].opcode;

	return write_ec_cmd(priv->priv->adev->handle, opcode, !blocked);
}