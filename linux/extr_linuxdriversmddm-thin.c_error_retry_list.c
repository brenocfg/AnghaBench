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
 int /*<<< orphan*/  error_retry_list_with_code (struct pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pool_io_error_code (struct pool*) ; 

__attribute__((used)) static void error_retry_list(struct pool *pool)
{
	error_retry_list_with_code(pool, get_pool_io_error_code(pool));
}