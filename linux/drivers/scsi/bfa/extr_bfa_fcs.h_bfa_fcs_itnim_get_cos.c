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
struct bfa_fcs_itnim_s {TYPE_1__* rport; } ;
typedef  enum fc_cos { ____Placeholder_fc_cos } fc_cos ;
struct TYPE_2__ {int fc_cos; } ;

/* Variables and functions */

__attribute__((used)) static inline	enum fc_cos
bfa_fcs_itnim_get_cos(struct bfa_fcs_itnim_s *itnim)
{
	return itnim->rport->fc_cos;
}