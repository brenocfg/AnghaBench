#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct virtio_vsock_pkt {int len; int buf_len; TYPE_1__* buf; TYPE_1__ hdr; } ;
struct vhost_virtqueue {int /*<<< orphan*/  iov; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VIRTIO_VSOCK_MAX_PKT_BUF_SIZE ; 
 scalar_t__ VIRTIO_VSOCK_TYPE_STREAM ; 
 int /*<<< orphan*/  WRITE ; 
 size_t copy_from_iter (TYPE_1__*,int,struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_init (struct iov_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,size_t) ; 
 size_t iov_length (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct virtio_vsock_pkt*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct virtio_vsock_pkt* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_transport_free_pkt (struct virtio_vsock_pkt*) ; 
 int /*<<< orphan*/  vq_err (struct vhost_virtqueue*,char*,int,...) ; 

__attribute__((used)) static struct virtio_vsock_pkt *
vhost_vsock_alloc_pkt(struct vhost_virtqueue *vq,
		      unsigned int out, unsigned int in)
{
	struct virtio_vsock_pkt *pkt;
	struct iov_iter iov_iter;
	size_t nbytes;
	size_t len;

	if (in != 0) {
		vq_err(vq, "Expected 0 input buffers, got %u\n", in);
		return NULL;
	}

	pkt = kzalloc(sizeof(*pkt), GFP_KERNEL);
	if (!pkt)
		return NULL;

	len = iov_length(vq->iov, out);
	iov_iter_init(&iov_iter, WRITE, vq->iov, out, len);

	nbytes = copy_from_iter(&pkt->hdr, sizeof(pkt->hdr), &iov_iter);
	if (nbytes != sizeof(pkt->hdr)) {
		vq_err(vq, "Expected %zu bytes for pkt->hdr, got %zu bytes\n",
		       sizeof(pkt->hdr), nbytes);
		kfree(pkt);
		return NULL;
	}

	if (le16_to_cpu(pkt->hdr.type) == VIRTIO_VSOCK_TYPE_STREAM)
		pkt->len = le32_to_cpu(pkt->hdr.len);

	/* No payload */
	if (!pkt->len)
		return pkt;

	/* The pkt is too big */
	if (pkt->len > VIRTIO_VSOCK_MAX_PKT_BUF_SIZE) {
		kfree(pkt);
		return NULL;
	}

	pkt->buf = kmalloc(pkt->len, GFP_KERNEL);
	if (!pkt->buf) {
		kfree(pkt);
		return NULL;
	}

	pkt->buf_len = pkt->len;

	nbytes = copy_from_iter(pkt->buf, pkt->len, &iov_iter);
	if (nbytes != pkt->len) {
		vq_err(vq, "Expected %u byte payload, got %zu bytes\n",
		       pkt->len, nbytes);
		virtio_transport_free_pkt(pkt);
		return NULL;
	}

	return pkt;
}