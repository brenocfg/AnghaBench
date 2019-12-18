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
typedef  size_t u16 ;
struct wil_status_ring {int is_rx; size_t size; size_t elem_size; int desc_rdy_pol; int /*<<< orphan*/  rx_data; } ;
struct wil6210_priv {struct wil_status_ring* srings; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,size_t,size_t) ; 
 int wil_sring_alloc (struct wil6210_priv*,struct wil_status_ring*) ; 
 int /*<<< orphan*/  wil_sring_free (struct wil6210_priv*,struct wil_status_ring*) ; 
 int wil_wmi_rx_sring_add (struct wil6210_priv*,size_t) ; 

__attribute__((used)) static int wil_init_rx_sring(struct wil6210_priv *wil,
			     u16 status_ring_size,
			     size_t elem_size,
			     u16 ring_id)
{
	struct wil_status_ring *sring = &wil->srings[ring_id];
	int rc;

	wil_dbg_misc(wil, "init RX sring: size=%u, ring_id=%u\n",
		     status_ring_size, ring_id);

	memset(&sring->rx_data, 0, sizeof(sring->rx_data));

	sring->is_rx = true;
	sring->size = status_ring_size;
	sring->elem_size = elem_size;
	rc = wil_sring_alloc(wil, sring);
	if (rc)
		return rc;

	rc = wil_wmi_rx_sring_add(wil, ring_id);
	if (rc)
		goto out_free;

	sring->desc_rdy_pol = 1;

	return 0;
out_free:
	wil_sring_free(wil, sring);
	return rc;
}