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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct uea_softc {int /*<<< orphan*/  data1; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  E4_MAKEFUNCTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E4_MEMACCESS ; 
 int /*<<< orphan*/  E4_REQUESTREAD ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int uea_cmv_e4 (struct uea_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int uea_read_cmv_e4(struct uea_softc *sc,
		u8 size, u16 group, u16 address, u16 offset, u32 *data)
{
	int ret = uea_cmv_e4(sc, E4_MAKEFUNCTION(E4_MEMACCESS,
							E4_REQUESTREAD, size),
			  group, address, offset, 0);
	if (ret < 0)
		uea_err(INS_TO_USBDEV(sc),
			"reading cmv failed with error %d\n", ret);
	else {
		*data = sc->data;
		/* size is in 16-bit word quantities */
		if (size > 2)
			*(data + 1) = sc->data1;
	}
	return ret;
}