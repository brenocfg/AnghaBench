#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WSM_GET32 (struct wsm_buf*) ; 
 scalar_t__ WSM_STATUS_SUCCESS ; 

__attribute__((used)) static int wsm_generic_confirm(struct cw1200_common *priv,
			     void *arg,
			     struct wsm_buf *buf)
{
	u32 status = WSM_GET32(buf);
	if (status != WSM_STATUS_SUCCESS)
		return -EINVAL;
	return 0;

underflow:
	WARN_ON(1);
	return -EINVAL;
}