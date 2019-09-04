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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct tifm_dev {TYPE_1__ dev; } ;
struct tifm_adapter {int (* has_ms_pif ) (struct tifm_adapter*,struct tifm_dev*) ;} ;

/* Variables and functions */
 struct tifm_adapter* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int stub1 (struct tifm_adapter*,struct tifm_dev*) ; 

int tifm_has_ms_pif(struct tifm_dev *sock)
{
	struct tifm_adapter *fm = dev_get_drvdata(sock->dev.parent);
	return fm->has_ms_pif(fm, sock);
}