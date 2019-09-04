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
struct safexcel_inv_result {int error; int /*<<< orphan*/  completion; } ;
struct crypto_async_request {struct safexcel_inv_result* data; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void safexcel_inv_complete(struct crypto_async_request *req, int error)
{
	struct safexcel_inv_result *result = req->data;

	if (error == -EINPROGRESS)
		return;

	result->error = error;
	complete(&result->completion);
}