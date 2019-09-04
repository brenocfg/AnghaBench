#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct s5p_aes_dev {TYPE_1__* req; } ;
struct TYPE_2__ {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 scalar_t__ sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void s5p_free_sg_cpy(struct s5p_aes_dev *dev, struct scatterlist **sg)
{
	int len;

	if (!*sg)
		return;

	len = ALIGN(dev->req->nbytes, AES_BLOCK_SIZE);
	free_pages((unsigned long)sg_virt(*sg), get_order(len));

	kfree(*sg);
	*sg = NULL;
}