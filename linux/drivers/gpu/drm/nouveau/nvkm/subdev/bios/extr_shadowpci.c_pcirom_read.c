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
typedef  scalar_t__ u32 ;
struct priv {scalar_t__ size; scalar_t__ rom; } ;
struct nvkm_bios {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32
pcirom_read(void *data, u32 offset, u32 length, struct nvkm_bios *bios)
{
	struct priv *priv = data;
	if (offset + length <= priv->size) {
		memcpy_fromio(bios->data + offset, priv->rom + offset, length);
		return length;
	}
	return 0;
}