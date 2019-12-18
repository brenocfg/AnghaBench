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
struct ucsi {TYPE_1__* ppm; } ;
struct TYPE_2__ {int (* sync ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static inline int ucsi_sync(struct ucsi *ucsi)
{
	if (ucsi->ppm && ucsi->ppm->sync)
		return ucsi->ppm->sync(ucsi->ppm);
	return 0;
}