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
typedef  int /*<<< orphan*/  u8 ;
struct virtrng_info {int /*<<< orphan*/  vq; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  virtqueue_add_inbuf (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void register_buffer(struct virtrng_info *vi, u8 *buf, size_t size)
{
	struct scatterlist sg;

	sg_init_one(&sg, buf, size);

	/* There should always be room for one buffer. */
	virtqueue_add_inbuf(vi->vq, &sg, 1, buf, GFP_KERNEL);

	virtqueue_kick(vi->vq);
}