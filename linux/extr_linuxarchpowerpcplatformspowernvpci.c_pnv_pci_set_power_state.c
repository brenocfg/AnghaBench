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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct opal_msg {int dummy; } ;
typedef  int /*<<< orphan*/  m ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 scalar_t__ OPAL_ASYNC_COMPLETION ; 
 int /*<<< orphan*/  OPAL_PCI_SET_POWER_STATE ; 
 scalar_t__ OPAL_SUCCESS ; 
 int /*<<< orphan*/  memcpy (struct opal_msg*,struct opal_msg*,int) ; 
 int opal_async_get_token_interruptible () ; 
 int /*<<< orphan*/  opal_async_release_token (int) ; 
 int opal_async_wait_response (int,struct opal_msg*) ; 
 int /*<<< orphan*/  opal_check_token (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_pci_set_power_state (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int pnv_pci_set_power_state(uint64_t id, uint8_t state, struct opal_msg *msg)
{
	struct opal_msg m;
	int token, ret;
	int64_t rc;

	if (!opal_check_token(OPAL_PCI_SET_POWER_STATE))
		return -ENXIO;

	token = opal_async_get_token_interruptible();
	if (unlikely(token < 0))
		return token;

	rc = opal_pci_set_power_state(token, id, (uint64_t)&state);
	if (rc == OPAL_SUCCESS) {
		ret = 0;
		goto exit;
	} else if (rc != OPAL_ASYNC_COMPLETION) {
		ret = -EIO;
		goto exit;
	}

	ret = opal_async_wait_response(token, &m);
	if (ret < 0)
		goto exit;

	if (msg) {
		ret = 1;
		memcpy(msg, &m, sizeof(m));
	}

exit:
	opal_async_release_token(token);
	return ret;
}