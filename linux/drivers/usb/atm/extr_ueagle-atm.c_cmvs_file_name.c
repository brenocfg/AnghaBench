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
struct uea_softc {size_t modem_index; } ;

/* Variables and functions */
 scalar_t__ ADI930 ; 
 scalar_t__ EAGLE_IV ; 
 int /*<<< orphan*/  FW_DIR ; 
 scalar_t__ IS_ISDN (struct uea_softc*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ UEA_CHIP_VERSION (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_FW_NAME_MAX ; 
 char** cmv_file ; 
 int /*<<< orphan*/  kernel_param_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_param_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char* const,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmvs_file_name(struct uea_softc *sc, char *const cmv_name, int ver)
{
	char file_arr[] = "CMVxy.bin";
	char *file;

	kernel_param_lock(THIS_MODULE);
	/* set proper name corresponding modem version and line type */
	if (cmv_file[sc->modem_index] == NULL) {
		if (UEA_CHIP_VERSION(sc) == ADI930)
			file_arr[3] = '9';
		else if (UEA_CHIP_VERSION(sc) == EAGLE_IV)
			file_arr[3] = '4';
		else
			file_arr[3] = 'e';

		file_arr[4] = IS_ISDN(sc) ? 'i' : 'p';
		file = file_arr;
	} else
		file = cmv_file[sc->modem_index];

	strcpy(cmv_name, FW_DIR);
	strlcat(cmv_name, file, UEA_FW_NAME_MAX);
	if (ver == 2)
		strlcat(cmv_name, ".v2", UEA_FW_NAME_MAX);
	kernel_param_unlock(THIS_MODULE);
}