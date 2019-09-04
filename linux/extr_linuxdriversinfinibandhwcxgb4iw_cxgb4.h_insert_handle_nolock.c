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
typedef  int /*<<< orphan*/  u32 ;
struct idr {int dummy; } ;
struct c4iw_dev {int dummy; } ;

/* Variables and functions */
 int _insert_handle (struct c4iw_dev*,struct idr*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int insert_handle_nolock(struct c4iw_dev *rhp, struct idr *idr,
				       void *handle, u32 id)
{
	return _insert_handle(rhp, idr, handle, id, 0);
}