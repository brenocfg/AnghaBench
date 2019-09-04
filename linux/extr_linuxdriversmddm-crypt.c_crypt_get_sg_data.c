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
struct scatterlist {int dummy; } ;
struct crypt_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypt_integrity_aead (struct crypt_config*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct scatterlist *crypt_get_sg_data(struct crypt_config *cc,
					     struct scatterlist *sg)
{
	if (unlikely(crypt_integrity_aead(cc)))
		return &sg[2];

	return sg;
}