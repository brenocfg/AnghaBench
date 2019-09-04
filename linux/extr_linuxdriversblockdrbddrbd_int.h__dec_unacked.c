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
struct drbd_device {int /*<<< orphan*/  unacked_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_IF_CNT_IS_NEGATIVE (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unacked_cnt ; 

__attribute__((used)) static inline void _dec_unacked(struct drbd_device *device, const char *func, int line)
{
	atomic_dec(&device->unacked_cnt);
	ERR_IF_CNT_IS_NEGATIVE(unacked_cnt, func, line);
}