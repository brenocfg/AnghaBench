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
typedef  scalar_t__ u64 ;
struct vhost_vsock {scalar_t__ guest_cid; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EINVAL ; 
 scalar_t__ U32_MAX ; 
 scalar_t__ VMADDR_CID_HOST ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hash_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vhost_vsock* vhost_vsock_get (scalar_t__) ; 
 int /*<<< orphan*/  vhost_vsock_hash ; 
 int /*<<< orphan*/  vhost_vsock_mutex ; 

__attribute__((used)) static int vhost_vsock_set_cid(struct vhost_vsock *vsock, u64 guest_cid)
{
	struct vhost_vsock *other;

	/* Refuse reserved CIDs */
	if (guest_cid <= VMADDR_CID_HOST ||
	    guest_cid == U32_MAX)
		return -EINVAL;

	/* 64-bit CIDs are not yet supported */
	if (guest_cid > U32_MAX)
		return -EINVAL;

	/* Refuse if CID is already in use */
	mutex_lock(&vhost_vsock_mutex);
	other = vhost_vsock_get(guest_cid);
	if (other && other != vsock) {
		mutex_unlock(&vhost_vsock_mutex);
		return -EADDRINUSE;
	}

	if (vsock->guest_cid)
		hash_del_rcu(&vsock->hash);

	vsock->guest_cid = guest_cid;
	hash_add_rcu(vhost_vsock_hash, &vsock->hash, vsock->guest_cid);
	mutex_unlock(&vhost_vsock_mutex);

	return 0;
}