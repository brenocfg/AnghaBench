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
struct pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_pool_mode (struct pool*) ; 
 int is_read_only_pool_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_read_only(struct pool *pool)
{
	return is_read_only_pool_mode(get_pool_mode(pool));
}