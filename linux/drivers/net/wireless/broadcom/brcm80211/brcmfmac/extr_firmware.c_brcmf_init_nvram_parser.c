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
typedef  int /*<<< orphan*/  u32 ;
struct nvram_parser {int line; int column; int /*<<< orphan*/  nvram; int /*<<< orphan*/  const* data; } ;

/* Variables and functions */
 size_t BRCMF_FW_MAX_NVRAM_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvram_parser*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcmf_init_nvram_parser(struct nvram_parser *nvp,
				   const u8 *data, size_t data_len)
{
	size_t size;

	memset(nvp, 0, sizeof(*nvp));
	nvp->data = data;
	/* Limit size to MAX_NVRAM_SIZE, some files contain lot of comment */
	if (data_len > BRCMF_FW_MAX_NVRAM_SIZE)
		size = BRCMF_FW_MAX_NVRAM_SIZE;
	else
		size = data_len;
	/* Alloc for extra 0 byte + roundup by 4 + length field */
	size += 1 + 3 + sizeof(u32);
	nvp->nvram = kzalloc(size, GFP_KERNEL);
	if (!nvp->nvram)
		return -ENOMEM;

	nvp->line = 1;
	nvp->column = 1;
	return 0;
}