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
typedef  int uint ;
struct wil_ring {int size; int is_rx; scalar_t__ va; } ;
struct wil6210_priv {struct wil_ring ring_rx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_rx_buf_len_init (struct wil6210_priv*) ; 
 int wil_rx_refill (struct wil6210_priv*,int) ; 
 int wil_vring_alloc (struct wil6210_priv*,struct wil_ring*) ; 
 int /*<<< orphan*/  wil_vring_free (struct wil6210_priv*,struct wil_ring*) ; 
 int wmi_rx_chain_add (struct wil6210_priv*,struct wil_ring*) ; 

__attribute__((used)) static int wil_rx_init(struct wil6210_priv *wil, uint order)
{
	struct wil_ring *vring = &wil->ring_rx;
	int rc;

	wil_dbg_misc(wil, "rx_init\n");

	if (vring->va) {
		wil_err(wil, "Rx ring already allocated\n");
		return -EINVAL;
	}

	wil_rx_buf_len_init(wil);

	vring->size = 1 << order;
	vring->is_rx = true;
	rc = wil_vring_alloc(wil, vring);
	if (rc)
		return rc;

	rc = wmi_rx_chain_add(wil, vring);
	if (rc)
		goto err_free;

	rc = wil_rx_refill(wil, vring->size);
	if (rc)
		goto err_free;

	return 0;
 err_free:
	wil_vring_free(wil, vring);

	return rc;
}