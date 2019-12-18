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
struct gb_camera {int dummy; } ;

/* Variables and functions */
 int gb_camera_flush (struct gb_camera*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_camera_op_flush(void *priv, u32 *request_id)
{
	struct gb_camera *gcam = priv;

	return gb_camera_flush(gcam, request_id);
}