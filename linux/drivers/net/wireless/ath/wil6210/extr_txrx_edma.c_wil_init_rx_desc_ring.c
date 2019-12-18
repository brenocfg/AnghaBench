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
typedef  int /*<<< orphan*/  u16 ;
struct wil_ring {int is_rx; int /*<<< orphan*/  size; } ;
struct wil6210_priv {struct wil_ring ring_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int wil_ring_alloc_desc_ring (struct wil6210_priv*,struct wil_ring*) ; 
 int /*<<< orphan*/  wil_ring_free_edma (struct wil6210_priv*,struct wil_ring*) ; 
 int wil_wmi_rx_desc_ring_add (struct wil6210_priv*,int) ; 

__attribute__((used)) static int wil_init_rx_desc_ring(struct wil6210_priv *wil, u16 desc_ring_size,
				 int status_ring_id)
{
	struct wil_ring *ring = &wil->ring_rx;
	int rc;

	wil_dbg_misc(wil, "init RX desc ring\n");

	ring->size = desc_ring_size;
	ring->is_rx = true;
	rc = wil_ring_alloc_desc_ring(wil, ring);
	if (rc)
		return rc;

	rc = wil_wmi_rx_desc_ring_add(wil, status_ring_id);
	if (rc)
		goto out_free;

	return 0;
out_free:
	wil_ring_free_edma(wil, ring);
	return rc;
}