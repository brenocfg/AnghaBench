#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct s5p_aes_dev {TYPE_1__* req; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* complete ) (TYPE_2__*,int) ;} ;
struct TYPE_3__ {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void s5p_aes_complete(struct s5p_aes_dev *dev, int err)
{
	dev->req->base.complete(&dev->req->base, err);
}