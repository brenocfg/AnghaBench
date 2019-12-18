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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {scalar_t__ base; } ;
struct brcmf_core_priv {TYPE_3__ pub; TYPE_2__* chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read32 ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 brcmf_chip_core_read32(struct brcmf_core_priv *core, u16 reg)
{
	return core->chip->ops->read32(core->chip->ctx, core->pub.base + reg);
}