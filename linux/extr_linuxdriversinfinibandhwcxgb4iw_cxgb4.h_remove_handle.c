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
 int /*<<< orphan*/  _remove_handle (struct c4iw_dev*,struct idr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void remove_handle(struct c4iw_dev *rhp, struct idr *idr, u32 id)
{
	_remove_handle(rhp, idr, id, 1);
}