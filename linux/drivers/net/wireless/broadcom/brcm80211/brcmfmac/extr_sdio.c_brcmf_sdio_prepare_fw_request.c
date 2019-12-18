#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct brcmf_sdio {TYPE_4__* sdiodev; TYPE_1__* ci; } ;
struct brcmf_fw_request {int /*<<< orphan*/  board_type; TYPE_2__* items; } ;
struct brcmf_fw_name {char* member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_8__ {TYPE_3__* settings; int /*<<< orphan*/  nvram_name; int /*<<< orphan*/  fw_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  board_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct brcmf_fw_name*) ; 
 int /*<<< orphan*/  BRCMF_FW_TYPE_BINARY ; 
 int /*<<< orphan*/  BRCMF_FW_TYPE_NVRAM ; 
 size_t BRCMF_SDIO_FW_CODE ; 
 size_t BRCMF_SDIO_FW_NVRAM ; 
 struct brcmf_fw_request* brcmf_fw_alloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmf_fw_name*,int /*<<< orphan*/ ,struct brcmf_fw_name*,int /*<<< orphan*/ ) ; 
 struct brcmf_fw_name* brcmf_sdio_fwnames ; 

__attribute__((used)) static struct brcmf_fw_request *
brcmf_sdio_prepare_fw_request(struct brcmf_sdio *bus)
{
	struct brcmf_fw_request *fwreq;
	struct brcmf_fw_name fwnames[] = {
		{ ".bin", bus->sdiodev->fw_name },
		{ ".txt", bus->sdiodev->nvram_name },
	};

	fwreq = brcmf_fw_alloc_request(bus->ci->chip, bus->ci->chiprev,
				       brcmf_sdio_fwnames,
				       ARRAY_SIZE(brcmf_sdio_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	if (!fwreq)
		return NULL;

	fwreq->items[BRCMF_SDIO_FW_CODE].type = BRCMF_FW_TYPE_BINARY;
	fwreq->items[BRCMF_SDIO_FW_NVRAM].type = BRCMF_FW_TYPE_NVRAM;
	fwreq->board_type = bus->sdiodev->settings->board_type;

	return fwreq;
}