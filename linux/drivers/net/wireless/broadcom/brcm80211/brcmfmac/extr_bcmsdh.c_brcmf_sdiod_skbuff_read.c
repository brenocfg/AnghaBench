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
typedef  unsigned int uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct sdio_func {int num; } ;
struct brcmf_sdio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_SDIOD_NOMEDIUM ; 
 int ENOMEDIUM ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  brcmf_sdiod_change_state (struct brcmf_sdio_dev*,int /*<<< orphan*/ ) ; 
 int sdio_memcpy_fromio (struct sdio_func*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int sdio_readsb (struct sdio_func*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int brcmf_sdiod_skbuff_read(struct brcmf_sdio_dev *sdiodev,
				   struct sdio_func *func, u32 addr,
				   struct sk_buff *skb)
{
	unsigned int req_sz;
	int err;

	/* Single skb use the standard mmc interface */
	req_sz = skb->len + 3;
	req_sz &= (uint)~3;

	switch (func->num) {
	case 1:
		err = sdio_memcpy_fromio(func, ((u8 *)(skb->data)), addr,
					 req_sz);
		break;
	case 2:
		err = sdio_readsb(func, ((u8 *)(skb->data)), addr, req_sz);
		break;
	default:
		/* bail out as things are really fishy here */
		WARN(1, "invalid sdio function number: %d\n", func->num);
		err = -ENOMEDIUM;
	}

	if (err == -ENOMEDIUM)
		brcmf_sdiod_change_state(sdiodev, BRCMF_SDIOD_NOMEDIUM);

	return err;
}