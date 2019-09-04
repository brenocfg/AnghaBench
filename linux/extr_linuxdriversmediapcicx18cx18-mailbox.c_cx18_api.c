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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int cx18_api_call (struct cx18*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int cx18_api(struct cx18 *cx, u32 cmd, int args, u32 data[])
{
	return cx18_api_call(cx, cmd, args, data);
}