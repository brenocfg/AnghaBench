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
struct net_device {int dummy; } ;
struct TYPE_3__ {int ctrlmode_supported; int /*<<< orphan*/ * data_bittiming_const; int /*<<< orphan*/ * bittiming_const; int /*<<< orphan*/  do_get_berr_counter; int /*<<< orphan*/  do_set_mode; } ;
struct m_can_classdev {int version; TYPE_2__* ops; int /*<<< orphan*/  dev; TYPE_1__ can; int /*<<< orphan*/ * data_timing; int /*<<< orphan*/ * bit_timing; int /*<<< orphan*/  napi; int /*<<< orphan*/  is_peripheral; struct net_device* net; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) (struct m_can_classdev*) ;} ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_CTRLMODE_FD ; 
 int CAN_CTRLMODE_FD_NON_ISO ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_CAN_NAPI_WEIGHT ; 
 int /*<<< orphan*/  can_set_static_ctrlmode (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  m_can_bittiming_const_30X ; 
 int /*<<< orphan*/  m_can_bittiming_const_31X ; 
 int m_can_check_core_release (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_data_bittiming_const_30X ; 
 int /*<<< orphan*/  m_can_data_bittiming_const_31X ; 
 int /*<<< orphan*/  m_can_get_berr_counter ; 
 int /*<<< orphan*/  m_can_niso_supported (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_poll ; 
 int /*<<< orphan*/  m_can_set_mode ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct m_can_classdev*) ; 

__attribute__((used)) static int m_can_dev_setup(struct m_can_classdev *m_can_dev)
{
	struct net_device *dev = m_can_dev->net;
	int m_can_version;

	m_can_version = m_can_check_core_release(m_can_dev);
	/* return if unsupported version */
	if (!m_can_version) {
		dev_err(m_can_dev->dev, "Unsupported version number: %2d",
			m_can_version);
		return -EINVAL;
	}

	if (!m_can_dev->is_peripheral)
		netif_napi_add(dev, &m_can_dev->napi,
			       m_can_poll, M_CAN_NAPI_WEIGHT);

	/* Shared properties of all M_CAN versions */
	m_can_dev->version = m_can_version;
	m_can_dev->can.do_set_mode = m_can_set_mode;
	m_can_dev->can.do_get_berr_counter = m_can_get_berr_counter;

	/* Set M_CAN supported operations */
	m_can_dev->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
					CAN_CTRLMODE_LISTENONLY |
					CAN_CTRLMODE_BERR_REPORTING |
					CAN_CTRLMODE_FD;

	/* Set properties depending on M_CAN version */
	switch (m_can_dev->version) {
	case 30:
		/* CAN_CTRLMODE_FD_NON_ISO is fixed with M_CAN IP v3.0.x */
		can_set_static_ctrlmode(dev, CAN_CTRLMODE_FD_NON_ISO);
		m_can_dev->can.bittiming_const = m_can_dev->bit_timing ?
			m_can_dev->bit_timing : &m_can_bittiming_const_30X;

		m_can_dev->can.data_bittiming_const = m_can_dev->data_timing ?
						m_can_dev->data_timing :
						&m_can_data_bittiming_const_30X;
		break;
	case 31:
		/* CAN_CTRLMODE_FD_NON_ISO is fixed with M_CAN IP v3.1.x */
		can_set_static_ctrlmode(dev, CAN_CTRLMODE_FD_NON_ISO);
		m_can_dev->can.bittiming_const = m_can_dev->bit_timing ?
			m_can_dev->bit_timing : &m_can_bittiming_const_31X;

		m_can_dev->can.data_bittiming_const = m_can_dev->data_timing ?
						m_can_dev->data_timing :
						&m_can_data_bittiming_const_31X;
		break;
	case 32:
		m_can_dev->can.bittiming_const = m_can_dev->bit_timing ?
			m_can_dev->bit_timing : &m_can_bittiming_const_31X;

		m_can_dev->can.data_bittiming_const = m_can_dev->data_timing ?
						m_can_dev->data_timing :
						&m_can_data_bittiming_const_31X;

		m_can_dev->can.ctrlmode_supported |=
						(m_can_niso_supported(m_can_dev)
						? CAN_CTRLMODE_FD_NON_ISO
						: 0);
		break;
	default:
		dev_err(m_can_dev->dev, "Unsupported version number: %2d",
			m_can_dev->version);
		return -EINVAL;
	}

	if (m_can_dev->ops->init)
		m_can_dev->ops->init(m_can_dev);

	return 0;
}