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
struct TYPE_2__ {scalar_t__ uobject; } ;
struct mthca_pd {TYPE_1__ ibpd; } ;

/* Variables and functions */
 int MTHCA_INLINE_HEADER_SIZE ; 

__attribute__((used)) static inline int mthca_max_inline_data(struct mthca_pd *pd, int max_data_size)
{
	/* We don't support inline data for kernel QPs (yet). */
	return pd->ibpd.uobject ? max_data_size - MTHCA_INLINE_HEADER_SIZE : 0;
}