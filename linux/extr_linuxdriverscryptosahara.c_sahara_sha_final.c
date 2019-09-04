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
struct ahash_request {scalar_t__ nbytes; } ;

/* Variables and functions */
 int sahara_sha_enqueue (struct ahash_request*,int) ; 

__attribute__((used)) static int sahara_sha_final(struct ahash_request *req)
{
	req->nbytes = 0;
	return sahara_sha_enqueue(req, 1);
}