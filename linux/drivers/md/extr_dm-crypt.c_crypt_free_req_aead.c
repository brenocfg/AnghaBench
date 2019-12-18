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
struct dm_crypt_io {int dummy; } ;
struct crypt_config {int /*<<< orphan*/  req_pool; int /*<<< orphan*/  per_bio_data_size; } ;
struct bio {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 struct dm_crypt_io* dm_per_bio_data (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct aead_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypt_free_req_aead(struct crypt_config *cc,
				struct aead_request *req, struct bio *base_bio)
{
	struct dm_crypt_io *io = dm_per_bio_data(base_bio, cc->per_bio_data_size);

	if ((struct aead_request *)(io + 1) != req)
		mempool_free(req, &cc->req_pool);
}