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
struct napi_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_schedule (struct napi_struct*) ; 

__attribute__((used)) static void napi_schedule_wrapper(void *param)
{
	struct napi_struct *napi = param;

	napi_schedule(napi);
}