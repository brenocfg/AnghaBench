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
struct dm_crypt_request {int dummy; } ;
struct crypt_config {int dmreq_start; } ;

/* Variables and functions */

__attribute__((used)) static struct dm_crypt_request *dmreq_of_req(struct crypt_config *cc,
					     void *req)
{
	return (struct dm_crypt_request *)((char *)req + cc->dmreq_start);
}