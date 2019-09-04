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
struct cc_hw_desc {int dummy; } ;
struct aead_request {scalar_t__ assoclen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIN_HASH ; 
 int /*<<< orphan*/  cc_set_assoc_desc (struct aead_request*,int /*<<< orphan*/ ,struct cc_hw_desc*,unsigned int*) ; 

__attribute__((used)) static void cc_proc_header_desc(struct aead_request *req,
				struct cc_hw_desc desc[],
				unsigned int *seq_size)
{
	unsigned int idx = *seq_size;
	/* Hash associated data */
	if (req->assoclen > 0)
		cc_set_assoc_desc(req, DIN_HASH, desc, &idx);

	/* Hash IV */
	*seq_size = idx;
}