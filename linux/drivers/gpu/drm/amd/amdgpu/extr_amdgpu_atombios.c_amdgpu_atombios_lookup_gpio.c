#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct atom_context {int bios; } ;
struct amdgpu_gpio_rec {int valid; scalar_t__ id; int shift; int mask; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {struct atom_context* atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct _ATOM_GPIO_PIN_LUT {TYPE_2__* asGPIO_Pin; } ;
struct TYPE_4__ {scalar_t__ ucGPIO_ID; int ucGpioPinBitShift; int /*<<< orphan*/  usGpioPin_AIndex; } ;
typedef  TYPE_2__ ATOM_GPIO_PIN_ASSIGNMENT ;
typedef  int /*<<< orphan*/  ATOM_COMMON_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GPIO_Pin_LUT ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_atom_parse_data_header (struct atom_context*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct amdgpu_gpio_rec*,int /*<<< orphan*/ ,int) ; 

struct amdgpu_gpio_rec
amdgpu_atombios_lookup_gpio(struct amdgpu_device *adev,
			    u8 id)
{
	struct atom_context *ctx = adev->mode_info.atom_context;
	struct amdgpu_gpio_rec gpio;
	int index = GetIndexIntoMasterTable(DATA, GPIO_Pin_LUT);
	struct _ATOM_GPIO_PIN_LUT *gpio_info;
	ATOM_GPIO_PIN_ASSIGNMENT *pin;
	u16 data_offset, size;
	int i, num_indices;

	memset(&gpio, 0, sizeof(struct amdgpu_gpio_rec));
	gpio.valid = false;

	if (amdgpu_atom_parse_data_header(ctx, index, &size, NULL, NULL, &data_offset)) {
		gpio_info = (struct _ATOM_GPIO_PIN_LUT *)(ctx->bios + data_offset);

		num_indices = (size - sizeof(ATOM_COMMON_TABLE_HEADER)) /
			sizeof(ATOM_GPIO_PIN_ASSIGNMENT);

		pin = gpio_info->asGPIO_Pin;
		for (i = 0; i < num_indices; i++) {
			if (id == pin->ucGPIO_ID) {
				gpio.id = pin->ucGPIO_ID;
				gpio.reg = le16_to_cpu(pin->usGpioPin_AIndex);
				gpio.shift = pin->ucGpioPinBitShift;
				gpio.mask = (1 << pin->ucGpioPinBitShift);
				gpio.valid = true;
				break;
			}
			pin = (ATOM_GPIO_PIN_ASSIGNMENT *)
				((u8 *)pin + sizeof(ATOM_GPIO_PIN_ASSIGNMENT));
		}
	}

	return gpio;
}