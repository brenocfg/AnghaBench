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
struct loop_device {int use_dio; int /*<<< orphan*/  lo_backing_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  __loop_update_dio (struct loop_device*,int) ; 
 int io_is_direct (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void loop_update_dio(struct loop_device *lo)
{
	__loop_update_dio(lo, io_is_direct(lo->lo_backing_file) |
			lo->use_dio);
}