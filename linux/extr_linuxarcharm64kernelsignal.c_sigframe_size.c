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
struct rt_sigframe_user_layout {int /*<<< orphan*/  size; } ;
struct rt_sigframe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 size_t round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t sigframe_size(struct rt_sigframe_user_layout const *user)
{
	return round_up(max(user->size, sizeof(struct rt_sigframe)), 16);
}