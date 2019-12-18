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
struct usb_serial {int dummy; } ;
struct cp210x_serial_private {int partnum; int use_actual_rate; void* max_speed; void* min_speed; } ;
typedef  void* speed_t ;

/* Variables and functions */
#define  CP210X_PARTNUM_CP2101 136 
#define  CP210X_PARTNUM_CP2102 135 
#define  CP210X_PARTNUM_CP2102N_QFN20 134 
#define  CP210X_PARTNUM_CP2102N_QFN24 133 
#define  CP210X_PARTNUM_CP2102N_QFN28 132 
#define  CP210X_PARTNUM_CP2103 131 
#define  CP210X_PARTNUM_CP2104 130 
#define  CP210X_PARTNUM_CP2105 129 
#define  CP210X_PARTNUM_CP2108 128 
 int /*<<< orphan*/  cp210x_interface_num (struct usb_serial*) ; 
 struct cp210x_serial_private* usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static void cp210x_init_max_speed(struct usb_serial *serial)
{
	struct cp210x_serial_private *priv = usb_get_serial_data(serial);
	bool use_actual_rate = false;
	speed_t min = 300;
	speed_t max;

	switch (priv->partnum) {
	case CP210X_PARTNUM_CP2101:
		max = 921600;
		break;
	case CP210X_PARTNUM_CP2102:
	case CP210X_PARTNUM_CP2103:
		max = 1000000;
		break;
	case CP210X_PARTNUM_CP2104:
		use_actual_rate = true;
		max = 2000000;
		break;
	case CP210X_PARTNUM_CP2108:
		max = 2000000;
		break;
	case CP210X_PARTNUM_CP2105:
		if (cp210x_interface_num(serial) == 0) {
			use_actual_rate = true;
			max = 2000000;	/* ECI */
		} else {
			min = 2400;
			max = 921600;	/* SCI */
		}
		break;
	case CP210X_PARTNUM_CP2102N_QFN28:
	case CP210X_PARTNUM_CP2102N_QFN24:
	case CP210X_PARTNUM_CP2102N_QFN20:
		use_actual_rate = true;
		max = 3000000;
		break;
	default:
		max = 2000000;
		break;
	}

	priv->min_speed = min;
	priv->max_speed = max;
	priv->use_actual_rate = use_actual_rate;
}