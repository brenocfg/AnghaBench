#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tcq_rd; int tcq_ed; int tcq_st; } ;
struct TYPE_6__ {scalar_t__ host_tcq_wr; TYPE_1__ ffL; } ;
typedef  TYPE_2__ IADEV ;

/* Variables and functions */
 int /*<<< orphan*/  ia_hack_tcq (TYPE_2__*) ; 

__attribute__((used)) static int ia_avail_descs(IADEV *iadev) {
   int tmp = 0;
   ia_hack_tcq(iadev);
   if (iadev->host_tcq_wr >= iadev->ffL.tcq_rd)
      tmp = (iadev->host_tcq_wr - iadev->ffL.tcq_rd) / 2;
   else
      tmp = (iadev->ffL.tcq_ed - iadev->ffL.tcq_rd + 2 + iadev->host_tcq_wr -
                   iadev->ffL.tcq_st) / 2;
   return tmp;
}